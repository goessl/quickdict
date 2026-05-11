try:
    from ._quickdict import *
    from ._pyquickdict import *
except ImportError as e:
    import warnings
    warnings.warn(
        "C extension _quickdict not available. Falling back to pure Python implementation _pyquickdict (slower): " + str(e),
        ImportWarning,
        stacklevel = 2
    )
    from ._pyquickdict import pyqd_neg as qd_neg
    from ._pyquickdict import *
