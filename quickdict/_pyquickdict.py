"""quickdict module pure Python implementation."""



from typing import Any, TypeVar
from collections.abc import Mapping



__all__ = ('pyqd_neg', )



K, V = TypeVar('K'), TypeVar('V')



def pyqd_neg(m:Mapping[K,V]) -> dict[K,V]:
    """Return a dict with negated values.
    
    Python implementation.
    """
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    return {k:-v for k, v in m.items()}
