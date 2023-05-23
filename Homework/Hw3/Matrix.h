#ifndef __Matrix_h__
#define __Matrix_h__
#include <string>
class Matrix {
    public:
        // CONSTRUCTORS
        Matrix();
        Matrix(unsigned int row_counts, unsigned int col_counts, double fills);
        Matrix(const Matrix& m);
        Matrix& operator=(const Matrix& m); // OPERATOR OVERRIDER EQUAL
        ~Matrix(){clear();} // DESTRUCTOR

        // ACCESSORS
        unsigned int num_rows() const;
        unsigned int num_cols() const;
        bool get(const unsigned int& row, const unsigned int& col, double& d) const;

        // MODIFERS
        bool operator== (const Matrix& b);
        bool operator!= (const Matrix& b);
        bool set(const unsigned int& row, const unsigned int& col, double d);
        void multiply_by_coefficient(const double& coefficient);
        bool swap_row(const unsigned int& row_num, const unsigned int& target_row);
        void transpose();
        bool add(const Matrix& b);
        bool subtract(const Matrix& b);
        double* get_row(unsigned int row_num);
        double* get_col(unsigned int col_num);
        Matrix* quarter();

    private: // REPRESENTATIONS
        void clear();
        void copy(const Matrix& m);
        unsigned int row_count;
        unsigned int col_count;
        double** m_data;
    // GIVING ACCESS OF PRIVATE VARIABLES TO OPERATOR <<
    friend std::ostream& operator<< (std::ostream& out, const Matrix& m); 
};

std::ostream& operator<< (std::ostream& out, const Matrix& m);

#endif