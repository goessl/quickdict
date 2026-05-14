try:
    from ._filtering import *
except ImportError as e:
    import warnings
    warnings.warn(
        "C extension _filtering not available. Falling back to pure Python implementation _pyfiltering (slower): " + str(e),
        ImportWarning,
        stacklevel = 2
    )
    from ._pyfiltering import *
