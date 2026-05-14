import pytest
from quickdict.filtering import *



#filter

def test_filter_none():
    assert qd_filter(None, {}) == {}
    assert qd_filter(None, {1:0, 2:3}) == {2:3}
    assert qd_filter(None, {1:1, 2:2}) == {1:1, 2:2}
    assert qd_filter(None, {1:0, 2:0}) == {}

def test_filter_callable():
    p = lambda v: v > 1
    assert qd_filter(p, {}) == {}
    assert qd_filter(p, {1:1, 2:2, 3:0}) == {2:2}
    assert qd_filter(p, {1:2, 2:3}) == {1:2, 2:3}
    assert qd_filter(p, {1:0, 2:1}) == {}

def test_filter_type_error():
    with pytest.raises(TypeError):
        qd_filter(1, {})
    with pytest.raises(TypeError):
        qd_filter(None, 1)


#kfilter

def test_kfilter():
    p = lambda k: k > 1
    assert qd_kfilter(p, {}) == {}
    assert qd_kfilter(p, {1:'a', 2:'b', 3:'c'}) == {2:'b', 3:'c'}
    assert qd_kfilter(p, {2:'b', 3:'c'}) == {2:'b', 3:'c'}
    assert qd_kfilter(p, {1:'a'}) == {}

def test_kfilter_type_error():
    with pytest.raises(TypeError):
        qd_kfilter(None, {})
    with pytest.raises(TypeError):
        qd_kfilter(lambda k: k, 1)


#kvfilter

def test_kvfilter():
    p = lambda k, v: k > v
    assert qd_kvfilter(p, {}) == {}
    assert qd_kvfilter(p, {1:0, 2:3, 3:2}) == {1:0, 3:2}
    assert qd_kvfilter(p, {1:0, 2:1}) == {1:0, 2:1}
    assert qd_kvfilter(p, {1:2, 2:3}) == {}

def test_kvfilter_type_error():
    with pytest.raises(TypeError):
        qd_kvfilter(None, {})
    with pytest.raises(TypeError):
        qd_kvfilter(lambda k, v: True, 1)


#ifilter

def test_ifilter_none():
    m = {}
    assert qd_ifilter(None, m)==m and m=={}
    m = {1:0, 2:3}
    assert qd_ifilter(None, m)==m and m=={2:3}
    m = {1:1, 2:2}
    assert qd_ifilter(None, m)==m and m=={1:1, 2:2}
    m = {1:0, 2:0}
    assert qd_ifilter(None, m)==m and m=={}

def test_ifilter_callable():
    p = lambda v: v > 1
    m = {1:1, 2:2, 3:0}
    assert qd_ifilter(p, m)==m and m=={2:2}
    m = {1:2, 2:3}
    assert qd_ifilter(p, m)==m and m=={1:2, 2:3}
    m = {1:0, 2:1}
    assert qd_ifilter(p, m)==m and m=={}

def test_ifilter_type_error():
    with pytest.raises(TypeError):
        qd_ifilter(1, {})
    with pytest.raises(TypeError):
        qd_ifilter(None, 1)


#ikfilter

def test_ikfilter():
    p = lambda k: k > 1
    m = {}
    assert qd_ikfilter(p, m)==m and m=={}
    m = {1:'a', 2:'b', 3:'c'}
    assert qd_ikfilter(p, m)==m and m=={2:'b', 3:'c'}
    m = {2:'b', 3:'c'}
    assert qd_ikfilter(p, m)==m and m=={2:'b', 3:'c'}
    m = {1:'a'}
    assert qd_ikfilter(p, m)==m and m=={}

def test_ikfilter_type_error():
    with pytest.raises(TypeError):
        qd_ikfilter(None, {})
    with pytest.raises(TypeError):
        qd_ikfilter(lambda k: k, 1)


#ikvfilter

def test_ikvfilter():
    p = lambda k, v: k > v
    m = {}
    assert qd_ikvfilter(p, m)==m and m=={}
    m = {1:0, 2:3, 3:2}
    assert qd_ikvfilter(p, m)==m and m=={1:0, 3:2}
    m = {1:0, 2:1}
    assert qd_ikvfilter(p, m)==m and m=={1:0, 2:1}
    m = {1:2, 2:3}
    assert qd_ikvfilter(p, m)==m and m=={}

def test_qd_ikvfilter_type_error():
    with pytest.raises(TypeError):
        qd_ikvfilter(None, {})
    with pytest.raises(TypeError):
        qd_ikvfilter(lambda k, v: True, 1)
