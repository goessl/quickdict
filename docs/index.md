# quickdict

::: quickdict
    options:
      members: false

## Example

```python
>>> from quickdict import qd_neg, qd_ifilter
>>> qd_neg({0: 1, 2: -3})
{0: -1, 2: 3}
>>> d = {0: 1, 1: 0, 2: -3}
>>> qd_ifilter(None, d)
{0: 1, 2: -3}
```

## Installation

```console
pip install git+https://github.com/goessl/quickdict.git
```

## Usage

`quickdict` is a C extension with automatic pure Python fallback.

### [mapping](mapping.md)

| Function   | out-of-place                      | in-place                            |
| ---------- | --------------------------------- | ----------------------------------- |
| Unary plus | [`pos`][quickdict.mapping.qd_pos] | [`ipos`][quickdict.mapping.qd_ipos] |
| Negation   | [`neg`][quickdict.mapping.qd_neg] | [`ineg`][quickdict.mapping.qd_ineg] |

### [filtering](filtering.md)

| Function        | out-of-place                                  | in-place                                        |
| --------------- | --------------------------------------------- | ----------------------------------------------- |
| Filter by value | [`filter`][quickdict.filtering.qd_filter]     | [`ifilter`][quickdict.filtering.qd_ifilter]     |
| Filter by key   | [`kfilter`][quickdict.filtering.qd_kfilter]   | [`ikfilter`][quickdict.filtering.qd_ikfilter]   |
| Filter by item  | [`kvfilter`][quickdict.filtering.qd_kvfilter] | [`ikvfilter`][quickdict.filtering.qd_ikvfilter] |

## Performance

All functions are benchmarked with [perfplot](https://github.com/nschloe/perfplot) against the equivalent plain Python dict comprehension.

`quickdict` is about twice as fast as a dict comprehension.

![qd_neg](img/bench_neg.png)

![qd_filter](img/bench_filter.png)

## Roadmap

- [x] Deploy
- [x] Production
- [x] Ballin

## License (MIT)

Copyright (c) 2026 Sebastian Gössl

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
