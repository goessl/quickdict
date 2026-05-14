try:
    from ._mapping import *
except ImportError as e:
    import warnings
    warnings.warn(
        "C extension _mapping not available. Falling back to pure Python implementation _pymapping (slower): " + str(e),
        ImportWarning,
        stacklevel = 2
    )
    from ._pymapping import *
