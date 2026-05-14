from typing import Callable, TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('qd_map',  'qd_imap',
           'qd_pos',  'qd_ipos',
           'qd_neg',  'qd_ineg')



K, V, W = TypeVar('K'), TypeVar('V'), TypeVar('W')



def qd_map(p:Callable[[V],W], m:Mapping[K,V]) -> dict[K,W]: ...
def qd_imap(p:Callable[[V],V], m:MutableMapping[K,V]) -> MutableMapping[K,V]: ...

def qd_pos(m:Mapping[K,V]) -> dict[K,V]: ...
def qd_ipos(m:MutableMapping[K,V]) -> MutableMapping[K,V]: ...

def qd_neg(m:Mapping[K,V]) -> dict[K,V]: ...
def qd_ineg(m:MutableMapping[K,V]) -> MutableMapping[K,V]: ...
