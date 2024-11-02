import os
import unittest

def calc(flag):
    os.system(f"cat {flag} test1.txt > first")
    os.system(f"cat/s21_cat {flag} test1.txt > second")
    os.system(f"diff first second > result")

class TestCat(unittest.TestCase):

    def test_no_flag(self):
        calc("")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_b(self):
        calc("-b")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_e(self):
        calc("-e")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_n(self):
        calc("-n")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_s(self):
        calc("-s")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")

    def test_t(self):
        calc("-t")
        self.assertEqual(os.path.getsize("result"), 0, "ERROR")
        
if __name__ == '__main__':
    unittest.main()