import pytest
from quickdict.filtering import *



#filter

def test_filter_none():
    for f in (qd_filter, pyqd_filter):
        assert f(None, {}) == {}
        assert f(None, {1:0, 2:3}) == {2:3}
        assert f(None, {1:1, 2:2}) == {1:1, 2:2}
        assert f(None, {1:0, 2:0}) == {}

def test_filter_callable():
    p = lambda v: v > 1
    for f in (qd_filter, pyqd_filter):
        assert f(p, {}) == {}
        assert f(p, {1:1, 2:2, 3:0}) == {2:2}
        assert f(p, {1:2, 2:3}) == {1:2, 2:3}
        assert f(p, {1:0, 2:1}) == {}

def test_filter_type_error():
    for f in (qd_filter, pyqd_filter):
        with pytest.raises(TypeError):
            f(1, {})
        with pytest.raises(TypeError):
            f(None, 1)


#kfilter

def test_kfilter():
    p = lambda k: k > 1
    for f in (qd_kfilter, pyqd_kfilter):
        assert f(p, {}) == {}
        assert f(p, {1:'a', 2:'b', 3:'c'}) == {2:'b', 3:'c'}
        assert f(p, {2:'b', 3:'c'}) == {2:'b', 3:'c'}
        assert f(p, {1:'a'}) == {}

def test_kfilter_type_error():
    for f in (qd_kfilter, pyqd_kfilter):
        with pytest.raises(TypeError):
            f(None, {})
        with pytest.raises(TypeError):
            f(lambda k: k, 1)


#kvfilter

def test_kvfilter():
    p = lambda k, v: k > v
    for f in (qd_kvfilter, pyqd_kvfilter):
        assert f(p, {}) == {}
        assert f(p, {1:0, 2:3, 3:2}) == {1:0, 3:2}
        assert f(p, {1:0, 2:1}) == {1:0, 2:1}
        assert f(p, {1:2, 2:3}) == {}

def test_kvfilter_type_error():
    for f in (qd_kvfilter, pyqd_kvfilter):
        with pytest.raises(TypeError):
            f(None, {})
        with pytest.raises(TypeError):
            f(lambda k, v: True, 1)


#ifilter

def test_ifilter_none():
    for f in (qd_ifilter, pyqd_ifilter):
        m = {}
        assert f(None, m)==m and m=={}
        m = {1:0, 2:3}
        assert f(None, m)==m and m=={2:3}
        m = {1:1, 2:2}
        assert f(None, m)==m and m=={1:1, 2:2}
        m = {1:0, 2:0}
        assert f(None, m)==m and m=={}

def test_ifilter_callable():
    p = lambda v: v > 1
    for f in (qd_ifilter, pyqd_ifilter):
        m = {1:1, 2:2, 3:0}
        assert f(p, m)==m and m=={2:2}
        m = {1:2, 2:3}
        assert f(p, m)==m and m=={1:2, 2:3}
        m = {1:0, 2:1}
        assert f(p, m)==m and m=={}

def test_ifilter_type_error():
    for f in (qd_ifilter, pyqd_ifilter):
        with pytest.raises(TypeError):
            f(1, {})
        with pytest.raises(TypeError):
            f(None, 1)


#ikfilter

def test_ikfilter():
    p = lambda k: k > 1
    for f in (qd_ikfilter, pyqd_ikfilter):
        m = {}
        assert f(p, m)==m and m=={}
        m = {1:'a', 2:'b', 3:'c'}
        assert f(p, m)==m and m=={2:'b', 3:'c'}
        m = {2:'b', 3:'c'}
        assert f(p, m)==m and m=={2:'b', 3:'c'}
        m = {1:'a'}
        assert f(p, m)==m and m=={}

def test_ikfilter_type_error():
    for f in (qd_ikfilter, pyqd_ikfilter):
        with pytest.raises(TypeError):
            f(None, {})
        with pytest.raises(TypeError):
            f(lambda k: k, 1)


#ikvfilter

def test_ikvfilter():
    p = lambda k, v: k > v
    for f in (qd_ikvfilter, pyqd_ikvfilter):
        m = {}
        assert f(p, m)==m and m=={}
        m = {1:0, 2:3, 3:2}
        assert f(p, m)==m and m=={1:0, 3:2}
        m = {1:0, 2:1}
        assert f(p, m)==m and m=={1:0, 2:1}
        m = {1:2, 2:3}
        assert f(p, m)==m and m=={}

def test_qd_ikvfilter_type_error():
    for f in (qd_ikvfilter, pyqd_ikvfilter):
        with pytest.raises(TypeError):
            f(None, {})
        with pytest.raises(TypeError):
            f(lambda k, v: True, 1)
