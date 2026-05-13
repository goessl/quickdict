from typing import Callable, TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('qd_map',  'pyqd_map',
           'qd_imap', 'pyqd_imap',
           
           'qd_pos',  'pyqd_pos',
           'qd_ipos', 'pyqd_ipos',
           
           'qd_neg',  'pyqd_neg',
           'qd_ineg', 'pyqd_ineg')



K, V, W = TypeVar('K'), TypeVar('V'), TypeVar('W')



def qd_map(p:Callable[[V],W], m:Mapping[K,V]) -> dict[K,W]:
    """Return a `dict` with `p` applied to the values."""
    ...

def pyqd_map(p:Callable[[V],W], m:Mapping[K,V]) -> dict[K,W]:
    """Return a `dict` with `p` applied to the values."""
    ...

def qd_imap(p:Callable[[V],V], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Apply `p` to the values."""
    ...

def pyqd_imap(p:Callable[[V],V], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Apply `p` to the values."""
    ...


def qd_pos(m:Mapping[K,V]) -> dict[K,V]:
    """Return a `dict` with the unary plus operator applied to the values."""
    ...

def pyqd_pos(m:Mapping[K,V]) -> dict[K,V]:
    """Return a `dict` with the unary plus operator applied to the values."""
    ...

def qd_ipos(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Apply the unary plus operator to the values."""
    ...

def pyqd_ipos(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Apply the unary plus operator to the values."""
    ...


def qd_neg(m:Mapping[K,V]) -> dict[K,V]:
    """Return a `dict` with negated values."""
    ...

def pyqd_neg(m:Mapping[K,V]) -> dict[K,V]:
    """Return a `dict` with negated values."""
    ...

def qd_ineg(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Negate the values."""
    ...

def pyqd_ineg(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Negate the values."""
    ...
