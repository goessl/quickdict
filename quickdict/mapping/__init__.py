from ._pymapping import *

try:
    from ._mapping import *
except ImportError as e:
    import warnings
    warnings.warn(
        "C extension _mapping not available. Falling back to pure Python implementation _pymapping (slower): " + str(e),
        ImportWarning,
        stacklevel = 2
    )
    from ._pymapping import (
        pyqd_map as qd_map, pyqd_imap as qd_imap,
        pyqd_pos as qd_pos, pyqd_ipos as qd_ipos,
        pyqd_neg as qd_neg, pyqd_ineg as qd_ineg
    )
