import numpy as np

def make_read_mat_test_npy():

    A = np.array([[1.0, 2.0, 3.0,
                   4.0, 5.0, 6.0,
                   7.0, 8.0, 9.0]])
    
    np.save("read_mat_test.npy",A)

if __name__ == "__main__":
    make_read_mat_test_npy()