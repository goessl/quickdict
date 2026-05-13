from quickdict import *



def test_qd_map():
    assert qd_map(str, {}) == {}
    assert qd_map(str, {0:1, 2:-3}) == {0:'1', 2:'-3'}

def test_qd_imap():
    m = {}
    assert qd_imap(abs, m)==m and m=={}
    m = {0:1, 2:-3}
    assert qd_imap(abs, m)==m and m=={0:1, 2:3}


def test_qd_pos():
    assert qd_pos({}) == {}
    assert qd_pos({0:1, 2:-3}) == {0:+1, 2:-3}

def test_qd_ipos():
    m = {}
    assert qd_ipos(m)==m and m=={}
    m = {0:1, 2:-3}
    assert qd_ipos(m)==m and m=={0:+1, 2:-3}


def test_qd_neg():
    assert qd_neg({}) == {}
    assert qd_neg({0:1, 2:-3}) == {0:-1, 2:+3}

def test_qd_ineg():
    m = {}
    assert qd_ineg(m)==m and m=={}
    m = {0:1, 2:-3}
    assert qd_ineg(m)==m and m=={0:-1, 2:+3}
