from typing import TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('qd_pos',  'pyqd_pos',
           'qd_ipos', 'pyqd_ipos',
           
           'qd_neg',  'pyqd_neg',
           'qd_ineg', 'pyqd_ineg')



K, V = TypeVar('K'), TypeVar('V')



def qd_pos(m:Mapping[K,V]) -> dict[K,V]:
    """Return a dict with the unary plus operator applied to the values."""
    ...

def pyqd_pos(m:Mapping[K,V]) -> dict[K,V]:
    """Return a dict with the unary plus operator applied to the values."""
    ...

def qd_ipos(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Apply the unary plus operator to the values."""
    ...

def pyqd_ipos(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Apply the unary plus operator to the values."""
    ...


def qd_neg(m:Mapping[K,V]) -> dict[K,V]:
    """Return a dict with negated values."""
    ...

def pyqd_neg(m:Mapping[K,V]) -> dict[K,V]:
    """Return a dict with negated values."""
    ...

def qd_ineg(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Negate the values."""
    ...

def pyqd_ineg(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Negate the values."""
    ...
