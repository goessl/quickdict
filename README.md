# quickdict

Quick Python dictionary operations.
```python
>>> from quickdict import qd_neg, qd_ifilter
>>> qd_neg({0: 1, 2: -3})
{0: -1, 2: 3}
>>> d = {0: 1, 1: 0, 2: -3}
>>> qd_ifilter(d)
{0: 1, 2: -3}
```

## Installation

```console
pip install git+https://github.com/goessl/quickdict.git
```

## Usage

**Enjoy the [documentation webpage](https://goessl.github.io/quickdict).**

## Roadmap

- [x] Deploy
- [ ] Production
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
