from ._pyquickdict import *

try:
    from ._quickdict import *
except ImportError as e:
    import warnings
    warnings.warn(
        "C extension _quickdict not available. Falling back to pure Python implementation _pyquickdict (slower): " + str(e),
        ImportWarning,
        stacklevel = 2
    )
    from ._pyquickdict import (
        pyqd_pos as qd_pos,
        pyqd_neg as qd_neg
    )
