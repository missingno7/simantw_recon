"""Lightweight C text utilities: comment-aware scanning, function location, TU stubbing."""
from __future__ import annotations

import re

KEYWORDS = set('''auto break case char const continue default do double else enum extern float for goto if
int long register return short signed sizeof static struct switch typedef union unsigned void volatile while
far near huge cdecl pascal interrupt fortran __far _far _near __based _based __segment __segname'''.split())


def mask_comments_and_strings(text: str) -> str:
    """Return text of equal length with comment/string/char contents replaced by spaces.

    Delimiters of strings/chars are kept so the scanner still sees tokens in place.
    """
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == '/' and i + 1 < n and text[i + 1] == '*':
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != '\n':
                    out[k] = ' '
            i = j
        elif c == '/' and i + 1 < n and text[i + 1] == '/':
            j = text.find('\n', i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = ' '
            i = j
        elif c in '"\'':
            j = i + 1
            while j < n and text[j] != c:
                if text[j] == '\\':
                    j += 1
                j += 1
            for k in range(i + 1, min(j, n)):
                if out[k] != '\n':
                    out[k] = ' '
            i = j + 1
        else:
            i += 1
    return ''.join(out)


def strip_comments(text: str) -> str:
    """Remove comments (keeping newlines) but not string contents."""
    out = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == '/' and i + 1 < n and text[i + 1] == '*':
            e = text.find('*/', i + 2)
            e = n if e < 0 else e + 2
            out.append(' ' + '\n' * text.count('\n', i, e))
            i = e
        elif c == '/' and i + 1 < n and text[i + 1] == '/':
            e = text.find('\n', i)
            i = n if e < 0 else e
        elif c in '"\'':
            j = i + 1
            while j < n and text[j] != c:
                if text[j] == '\\':
                    j += 1
                j += 1
            out.append(text[i:j + 1])
            i = j + 1
        else:
            out.append(c)
            i += 1
    return ''.join(out)


def top_level_functions(text: str):
    """Yield dicts {name, header_start, body_start, body_end} for top-level function definitions.

    body_start is the index of '{', body_end the index after the matching '}'.
    """
    m = mask_comments_and_strings(text)
    depth = 0
    i, n = 0, len(m)
    last_stmt_end = 0  # index after previous top-level ';' or '}'
    results = []
    while i < n:
        c = m[i]
        if c == '{':
            if depth == 0:
                prev = m[last_stmt_end:i]
                stripped = prev.rstrip()
                # function body: header text ends with ')' (ANSI) or ';' (K&R param decls)
                is_func = False
                name = None
                if stripped.endswith(')') and '=' not in stripped.split(')')[-1]:
                    is_func = True
                elif stripped.endswith(';') and '(' in stripped:
                    is_func = True
                if is_func and not re.search(r'\b(struct|union|enum)\s*\w*\s*$', stripped):
                    # name: identifier before the first '(' that is followed by the param list
                    header = prev
                    name = _function_name(header)
                    if name is None:
                        is_func = False
                # find matching brace
                j, d = i, 0
                while j < n:
                    if m[j] == '{':
                        d += 1
                    elif m[j] == '}':
                        d -= 1
                        if d == 0:
                            break
                    j += 1
                if is_func:
                    hs = last_stmt_end
                    while hs < i and text[hs] in ' \t\r\n':
                        hs += 1
                    results.append({'name': name, 'header_start': hs, 'body_start': i, 'body_end': j + 1})
                    last_stmt_end = j + 1
                    i = j + 1
                    continue
                depth = 1
                i += 1
                continue
            depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0:
                pass
        elif c == ';' and depth == 0:
            last_stmt_end = i + 1
        i += 1
    return results


def _function_name(header: str):
    # Last top-level '(' group that is followed only by ')' ... ; the name precedes the
    # parameter list: find identifiers followed by '(' where the parenthesis closes at the
    # end (for ANSI) - handle `int (far *f(void))(int)` poorly but that is rare.
    names = [mm for mm in re.finditer(r'\b([A-Za-z_]\w*)\s*\(', header)]
    for mm in names:
        if mm.group(1) not in KEYWORDS:
            return mm.group(1)
    return None


def find_function(text: str, name: str):
    for f in top_level_functions(text):
        if f['name'] == name:
            return f
    raise KeyError(f'function {name} not found in source')


def stub_other_functions(text: str, keep: str):
    """Replace bodies of all top-level functions except `keep` with '{}'."""
    funcs = top_level_functions(text)
    out = []
    pos = 0
    for f in funcs:
        if f['name'] == keep:
            continue
        out.append(text[pos:f['body_start']])
        out.append('{}')
        pos = f['body_end']
    out.append(text[pos:])
    return ''.join(out)


def typedef_names(text: str):
    """Collect typedef names declared anywhere in the file (heuristic, top-level)."""
    m = mask_comments_and_strings(text)
    names = set()
    for mm in re.finditer(r'\btypedef\b', m):
        # statement until ';' at brace depth 0
        j, d = mm.end(), 0
        while j < len(m):
            if m[j] == '{':
                d += 1
            elif m[j] == '}':
                d -= 1
            elif m[j] == ';' and d == 0:
                break
            j += 1
        stmt = m[mm.end():j]
        stmt = re.sub(r'\{[^{}]*\}', ' ', stmt)
        while '{' in stmt:
            stmt = re.sub(r'\{[^{}]*\}', ' ', stmt)
        fp = re.search(r'\(\s*(?:far\s+|near\s+)?\*\s*(?:far\s+)?([A-Za-z_]\w*)\s*\)', stmt)
        if fp:
            names.add(fp.group(1))
            continue
        for part in stmt.split(','):
            ids = [x for x in re.findall(r'[A-Za-z_]\w*', re.sub(r'\[[^\]]*\]', '', part))
                   if x not in KEYWORDS]
            if ids:
                names.add(ids[-1])
    return names
