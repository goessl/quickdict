"""quickdict.mapping module pure Python implementation."""



from typing import Callable, TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('qd_map', 'qd_imap',
           'qd_pos', 'qd_ipos',
           'qd_neg', 'qd_ineg')



K, V, W = TypeVar('K'), TypeVar('V'), TypeVar('W')



def qd_map(p:Callable[[V],W], m:Mapping[K,V]) -> dict[K,W]:
    """Return a `dict` with `p` applied to the values.
    
    Python implementation.
    """
    if not callable(p):
        raise TypeError('p must be callable')
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    
    return {k:p(v) for k, v in m.items()}

def qd_imap(p:Callable[[V],V], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Apply `p` to the values.
    
    Python implementation.
    """
    if not callable(p):
        raise TypeError('p must be callable')
    if not isinstance(m, MutableMapping):
        raise TypeError('m must be a mutable mapping')
    
    for k, v in m.items():
        m[k] = p(v)
    return m


def qd_pos(m:Mapping[K,V]) -> dict[K,V]:
    """Return a `dict` with the unary plus operator applied to the values.
    
    Python implementation.
    """
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    
    return {k:+v for k, v in m.items()}

def qd_ipos(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Apply the unary plus operator to the values.
    
    Python implementation.
    """
    if not isinstance(m, MutableMapping):
        raise TypeError('m must be a mutable mapping')
    
    for k, v in m.items():
        m[k] = +v
    return m


def qd_neg(m:Mapping[K,V]) -> dict[K,V]:
    """Return a `dict` with negated values.
    
    Python implementation.
    """
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    
    return {k:-v for k, v in m.items()}

def qd_ineg(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Negate the values.
    
    Python implementation.
    """
    if not isinstance(m, MutableMapping):
        raise TypeError('m must be a mutable mapping')
    
    for k, v in m.items():
        m[k] = -v
    return m
