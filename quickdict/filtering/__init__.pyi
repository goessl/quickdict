from typing import Callable, TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('qd_filter',    'pyqd_filter',
           'qd_kfilter',   'pyqd_kfilter',
           'qd_kvfilter',  'pyqd_kvfilter',
           'qd_ifilter',   'pyqd_ifilter',
           'qd_ikfilter',  'pyqd_ikfilter',
           'qd_ikvfilter', 'pyqd_ikvfilter')



K, V = TypeVar('K'), TypeVar('V')



def qd_filter(p:None|Callable[[V],bool], m:Mapping[K,V]) -> dict[K,V]:
    """Return a filtered dict with the predicate applied to the values.
    
    `p` might be
    
    - `None`: filtered by `bool(v)`,
    - otherwise: filtered by `p(v)`.
    """
    ...

def pyqd_filter(p:None|Callable[[V],bool], m:Mapping[K,V]) -> dict[K,V]:
    """Return a filtered dict with the predicate applied to the values.
    
    `p` might be
    
    - `None`: filtered by `bool(v)`,
    - otherwise: filtered by `p(v)`.
    """
    ...


def qd_kfilter(p:Callable[[K],bool], m:Mapping[K,V]) -> dict[K,V]:
    """Return a filtered dict with the predicate applied to the keys.
    
    Filtered by `p(k)`.
    """
    ...

def pyqd_kfilter(p:Callable[[K],bool], m:Mapping[K,V]) -> dict[K,V]:
    """Return a filtered dict with the predicate applied to the keys.
    
    Filtered by `p(k)`.
    """
    ...


def qd_kvfilter(p:Callable[[K,V],bool], m:Mapping[K,V]) -> dict[K,V]:
    """Return a filtered dict with the predicate applied to the items.
    
    Filtered by `p(k, v)`.
    """
    ...

def pyqd_kvfilter(p:Callable[[K,V],bool], m:Mapping[K,V]) -> dict[K,V]:
    """Return a filtered dict with the predicate applied to the items.
    
    Filtered by `p(k, v)`.
    """
    ...


def qd_ifilter(p:None|Callable[[V],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Filter with the predicate applied to the values.
    
    `p` might be
    
    - `None`: filtered by `bool(v)`,
    - otherwise: filtered by `p(v)`.
    """
    ...

def pyqd_ifilter(p:None|Callable[[V],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Filter with the predicate applied to the values.
    
    `p` might be
    
    - `None`: filtered by `bool(v)`,
    - otherwise: filtered by `p(v)`.
    """
    ...


def qd_ikfilter(p:Callable[[K],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Filter a mapping with the predicate applied to the keys.
    
    Filtered by `p(k)`.
    """
    ...

def pyqd_ikfilter(p:Callable[[K],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Filter a mapping with the predicate applied to the keys.
    
    Filtered by `p(k)`.
    """
    ...


def qd_ikvfilter(p:Callable[[K,V],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Filter a mapping with the predicate applied to the items.
    
    Filtered by `p(k, v)`.
    """
    ...

def pyqd_ikvfilter(p:Callable[[K,V],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Filter a mapping with the predicate applied to the items.
    
    Filtered by `p(k, v)`.
    """
    ...
