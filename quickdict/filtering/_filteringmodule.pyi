from typing import Callable, TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('qd_filter',   'qd_ifilter',
           'qd_kfilter',  'qd_ikfilter',
           'qd_kvfilter', 'qd_ikvfilter')



K, V = TypeVar('K'), TypeVar('V')



def qd_filter(p:None|Callable[[V],bool], m:Mapping[K,V]) -> dict[K,V]: ...
def qd_kfilter(p:Callable[[K],bool], m:Mapping[K,V]) -> dict[K,V]: ...
def qd_kvfilter(p:Callable[[K,V],bool], m:Mapping[K,V]) -> dict[K,V]: ...

def qd_ifilter(p:None|Callable[[V],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]: ...
def qd_ikfilter(p:Callable[[K],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]: ...
def qd_ikvfilter(p:Callable[[K,V],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]: ...
