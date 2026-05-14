"""Performance benchmarks.

Run from the project root:
    python -P bench.py

-P so that the installed C extension is used.

Saves plots to docs/img/.
"""

import os
import perfplot
from operator import eq
from random import randint
from quickdict import *



os.makedirs('docs/img', exist_ok=True)

SETUP = lambda n: {i:randint(-1000, +1000) for i in range(n)}
N     = tuple(2**k for k in range(15))



perfplot.bench(
    setup          = SETUP,
    kernels        = (lambda m: {k:-v for k, v in m.items()},
                      qd_neg),
    labels         = ['{k:-v for k, v in m.items()}', 'qd_neg(m)'],
    n_range        = N,
    xlabel         = 'len(m)',
    title          = 'qd_neg',
    equality_check = eq
).save('docs/img/bench_neg.png')

perfplot.bench(
    setup          = SETUP,
    kernels        = (lambda m: {k:v for k, v in m.items() if v},
                      lambda m: qd_filter(None, m)),
    labels         = ['{k:v for k, v in m.items() if v}', 'qd_filter(None, m)'],
    n_range        = N,
    xlabel         = 'len(m)',
    title          = 'qd_filter',
    equality_check = eq
).save('docs/img/bench_filter.png')
