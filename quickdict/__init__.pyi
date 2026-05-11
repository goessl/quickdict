from typing import TypeVar
from collections.abc import Mapping



__all__ = ('qd_pos', 'pyqd_pos',
           'qd_neg', 'pyqd_neg')



K, V = TypeVar('K'), TypeVar('V')



def qd_pos(m:Mapping[K,V]) -> dict[K,V]: ...
def pyqd_pos(m:Mapping[K,V]) -> dict[K,V]: ...

def qd_neg(m:Mapping[K,V]) -> dict[K,V]: ...
def pyqd_neg(m:Mapping[K,V]) -> dict[K,V]: ...
