"""Small audited C89 expression classes, not arbitrary token mutation."""
import itertools
from common import FormatError

def generate(axis):
    kind=axis['generator']
    if kind=='local_order_register':
        names=axis['locals'];address_taken=set(axis.get('address_taken',[]));eligible=[n for n in names if n not in address_taken]
        for order in itertools.permutations(names):
            for quals in itertools.product(['','register '],repeat=len(eligible)):
                yield '\n'.join('    '+(quals[eligible.index(n)] if n in eligible else '')+axis.get('type','int')+' '+n+';' for n in order)
    elif kind=='u16_high_byte':
        name=axis.get('parameter','context');call=axis['call']
        expressions=[f'{name} & 0xff00',f'({name} >> 8) << 8',f'({name} / 256) * 256',f'{name} - (unsigned char){name}',f'(unsigned int)((unsigned char *)&{name})[1] << 8',f'((unsigned char *)&{name})[1] * 256U',f'{name} & ~255U',f'({name} | 255U) ^ 255U']
        for expression in expressions:
            for style in ['inline','reuse','temp','register','volatile']:
                declaration='' if style in ('inline','reuse') else ('register ' if style=='register' else 'volatile ' if style=='volatile' else '')+'unsigned int value;\n'
                assignment='' if style=='inline' else (name if style=='reuse' else 'value')+' = '+expression+';\n'
                arg=expression if style=='inline' else name if style=='reuse' else 'value'
                yield declaration+assignment+call.replace('@VALUE@',arg)
    elif kind=='signed_range_predicate':
        name=axis.get('parameter','value');lower=int(axis['lower']);upper=int(axis['upper'])
        if not -32768<=lower<=upper<=32767:raise FormatError('range must fit signed Win16 int')
        condition=f'{name} >= {lower} && {name} <= {upper}'
        yield 'return '+condition+';'
        yield 'if ('+condition+') return 1; return 0;'
        yield f'if ({name} < {lower} || {name} > {upper}) return 0; return 1;'
        yield f'if ({name} >= {lower}) {{ if ({name} <= {upper}) return 1; }} return 0;'
        yield f'int result; result=0; if ({condition}) result=1; return result;'
        yield f'return ({condition}) ? 1 : 0;'
        yield f'if ({name} <= {upper} && {name} >= {lower}) return 1; return 0;'
        yield f'return (unsigned int)((unsigned int){name} - (unsigned int)({lower})) <= {upper-lower}U;'
    else:raise FormatError('unknown semantic generator '+kind)
