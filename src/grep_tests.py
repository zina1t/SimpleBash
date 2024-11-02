import os
import unittest

def calc(pattern, flag):
    os.system(f"grep {flag} {pattern} test1.txt test2.txt test3.txt test4.txt > first")
    os.system(f"grep/s21_grep {flag} {pattern} test1.txt test2.txt test3.txt test4.txt > second")
    os.system(f"diff first second > result")

def calc_f(flag):
    os.system(f"grep {flag} test2.txt test4.txt > first")
    os.system(f"grep/s21_grep {flag} test2.txt test4.txt > second")
    os.system(f"diff first second > result")


def calc_o(flag, pattern):
    os.system(f"grep {flag} {pattern} test3.txt > first")
    os.system(f"grep/s21_grep {flag} {pattern} test3.txt > second")
    os.system(f"diff first second > result")


class TestGrep(unittest.TestCase):

    def test_no_flag(self):
        calc("no", "")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_i(self):
        calc("bober", "-i")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_v(self):
        calc("bek", "-v")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_c(self):
        calc("m", "-c")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_l(self):
        calc("a", "-l")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_n(self):
        calc("s", "-n")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_o(self):
        calc_o("-o", "bekbek")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_h(self):
        calc("bekbek", "-h")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_s(self):
        calc("123123S", "-s")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_f(self):
        calc_f("-f")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_in(self):
        calc("bek", "-in")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_lv(self):
        calc("pupuri", "-lv")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_ho(self):
        calc("123", "-ho")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_nf(self):
        calc_f("-nf")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_e(self):
        calc("love", "-e")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_in(self):
        calc("bek", "-in")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_lv(self):
        calc("saas", "-lv")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_ho(self):
        calc("abdfsdfO", "-ho")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_nf(self):
        calc_f("-nf")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_so(self):
        calc("bek", "-so")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_lh(self):
        calc("love", "-lh")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_flag_lo(self):
        calc("love", "-lo")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

if __name__ == '__main__':
    unittest.main()
