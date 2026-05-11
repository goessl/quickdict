from ._pyfiltering import *

try:
    from ._filtering import *
except ImportError as e:
    import warnings
    warnings.warn(
        "C extension _filtering not available. Falling back to pure Python implementation _pyfiltering (slower): " + str(e),
        ImportWarning,
        stacklevel = 2
    )
    from ._pyfiltering import (
        pyqd_filter as qd_filter, pyqd_ifilter as qd_ifilter
    )
