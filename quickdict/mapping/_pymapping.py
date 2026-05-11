"""quickdict.mapping module pure Python implementation."""



from typing import TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('pyqd_pos', 'pyqd_ipos',
           'pyqd_neg', 'pyqd_ineg')



K, V = TypeVar('K'), TypeVar('V')



def pyqd_pos(m:Mapping[K,V]) -> dict[K,V]:
    """Return a dict with the unary plus operator applied to the values.
    
    Python implementation.
    """
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    
    return {k:+v for k, v in m.items()}

def pyqd_ipos(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Apply the unary plus operator to the values.
    
    Python implementation.
    """
    if not isinstance(m, MutableMapping):
        raise TypeError('m must be a mutable mapping')
    
    for k, v in m.items():
        m[k] = +v
    return m


def pyqd_neg(m:Mapping[K,V]) -> dict[K,V]:
    """Return a dict with negated values.
    
    Python implementation.
    """
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    
    return {k:-v for k, v in m.items()}

def pyqd_ineg(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Negate the values.
    
    Python implementation.
    """
    if not isinstance(m, MutableMapping):
        raise TypeError('m must be a mutable mapping')
    
    for k, v in m.items():
        m[k] = -v
    return m
