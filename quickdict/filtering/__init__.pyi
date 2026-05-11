from typing import TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('qd_filter',  'pyqd_filter',
           'qd_ifilter', 'pyqd_ifilter')



K, V = TypeVar('K'), TypeVar('V')



def qd_filter(m:Mapping[K,V]) -> dict[K,V]: ...
def pyqd_filter(m:Mapping[K,V]) -> dict[K,V]: ...

def qd_ifilter(m:MutableMapping[K,V]) -> MutableMapping[K,V]: ...
def pyqd_ifilter(m:MutableMapping[K,V]) -> MutableMapping[K,V]: ...
