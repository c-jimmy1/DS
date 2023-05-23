#include "Matrix.h"
#include <iostream>

// EMPTY CONSTRUCTOR
Matrix::Matrix() {
    row_count = 0;
    col_count = 0;
    m_data = NULL;
}

// CONSTRUCTOR USING ALL PARAMETERS
Matrix::Matrix(unsigned int row_counts, unsigned int col_counts, double fills) {
    // IF EITHER ROWS OR COLS IS EQUAL 0 SET IT TO EMPTY
    if (row_counts == 0 || col_counts == 0) {
        row_count = 0;
        col_count = 0;
        m_data = NULL;
    }
    else {
        row_count = row_counts;
        col_count = col_counts;
        m_data = new double*[row_count]; // ALLOCATING MEMORY FOR NUMBER OF ROWS
        for (unsigned int i = 0; i < row_count; i++) {
            m_data[i] = new double[col_count]; // ALLOCATING MEMORY FOR NUMBER OF COLUMNS
            for (unsigned int j = 0; j < col_count; j++) { 
                // SETTING EACH INDEX TO THE FILL VALUE
                m_data[i][j] = fills;
            }
        }
        
    }
}

// COPY METHOD THAT CREATES A COPY OF MATRIX M PASSED IN
void Matrix::copy(const Matrix& m) {
    row_count = m.num_rows();
    col_count = m.num_cols();
    m_data = new double*[row_count]; // ALLOCATING MEMORY FOR NUMBER OF ROWS
    for (unsigned int i = 0; i < m.num_rows(); i++) {
        m_data[i] = new double[col_count]; // ALLOCATING MEMORY FOR NUMBER OF COLUMNS
        for (unsigned int j = 0; j < m.num_cols(); j++) {
           m.get(i, j, m_data[i][j]);
        }
    }
}

// CONSTRUCTOR FOR WHEN A MATRIX IS PASSED IN AS A PARAMETER
// SETS MATRIX 2 TO THE SAME AS MATRIX 1
Matrix::Matrix(const Matrix& m) {
    copy(m);
}

// CONSTRUCTOR FOR = OPERATOR, THE L VALUE MATRIX WILL BE THE SAME AS THE R VALUE MATRIX
Matrix& Matrix::operator=(const Matrix& m) {
    if (this != &m) {
        clear();
        copy(m);
    }
    return *this;
}

// THIS METHOD RETURNS THE TOTAL NUMBER OF ROWS
unsigned int Matrix::num_rows() const {
    return row_count;
}

// THIS METHOD RETURNS THE TOTAL NUMBER OF COLUMNS
unsigned int Matrix::num_cols() const {
    return col_count;
}

// OPERATOR OVERRIDER FOR == SIGN, COMPARES EACH VALUE IN MATRIX TO CHECK IF EQUAL
bool Matrix::operator== (const Matrix& b) {
    // CHECKING IF ROW COUNT AND COL COUNT ARE DIFFERENT
    if (b.row_count != row_count || b.col_count != col_count) {
        return false;
    }
    else {
        for (unsigned i = 0; i < row_count; i++) {
            for (unsigned j = 0; j < col_count; j++) {
                if (m_data[i][j] != b.m_data[i][j]) {
                    return false;
                }
            }
        }
    }
    return true;
    }

// OPERATOR OVERRIDER FOR != SIGN, USES THE == OPERATOR; IF == IS TRUE, RETURN THE OPPOSITE
bool Matrix::operator!= (const Matrix& b) {
    return !(*this == b);
}

// CLEARING A MATRIX BY DELETING THE POINTER AND THE POINTER OF POINTERS
// ALSO RESETS ROW COUNT AND COL COUNT
void Matrix::clear() {
    for(unsigned int i = 0; i < row_count; i++) {
        delete[] m_data[i];
    }
    delete[] m_data;
    m_data = NULL;
    row_count = 0;
    col_count = 0;
}

// GETS THE VALUE OF AN INDEX AND PUTS IT A DOUBLE CALLED d
// PARAMETERS TAKES IN THE ROW WANTED AND COL WANTED
bool Matrix::get(const unsigned int& row, const unsigned int& col, double& d) const {
    // IF STATEMENT MAKING SURE THE ROW AND COL THE USER WANTS IS WITHIN RANGE
    if (row < row_count && col < col_count) {
        d = m_data[row][col];
        return true;
    }
    else {
        return false;
    }
}

// THIS METHOD ALLOWS CHANGES TO A VALUE AT A GIVEN ROW AND COL
bool Matrix::set(const unsigned int& row, const unsigned int& col, double d) {
    // IF STATEMENT MAKING SURE THE ROW AND COL THE USER WANTS IS WITHIN RANGE
    if (row < row_count && col < col_count) {
        m_data[row][col] = d;
        return true;
    }
    else {
        return false;
    }
}

// OPERATOR OVERRIDER FOR PRINTING
std::ostream& operator<< (std::ostream& out, const Matrix& m) {
    // IF THE ROW AND COLUMN SIZE IS 0, CREATE EMPTY BRACKETS
    if (m.row_count == 0 && m.col_count == 0) {
        out << "[";
        out << " ]" << std::endl;
    }
    else {
        out << "["; // INITIAL BRACKET
        for (unsigned int i = 0; i < m.row_count; i++) {
            for (unsigned int j = 0; j < m.col_count; j++) {
                // IF ITS THE FIRST ROW PRINT SPACE BEFORE THE VALUE
                if (i == 0) {
                    out << " " << m.m_data[i][j]; 
                    if (j == m.col_count - 1) { // IF THE COLUMN IS THE LAST COLUMN START A NEW LINE
                        out << std::endl;
                    }
                }
                else if (i == m.row_count - 1) { 
                    if (j == 0) { // IF ITS THE LAST ROW AND THE COLUMN IS THE FIRST, ADD SPACE
                        out << " ";
                    }
                    out << " " << m.m_data[i][j];
                    if (j == m.col_count - 1) { // IF THE COLUMN IS THE LAST, ADD A CLOSING BRACKET
                        out << " ]" << std::endl;
                    }
                }
                else {
                    if (j == 0) { // IF THE COLUMN IS THE FIRST, ADD SPACE
                        out << " ";
                    }
                    out << " " << m.m_data[i][j];
                    if (j == m.col_count - 1) { // IF THE COLUMN IS THE LAST, GO TO A NEW LINE
                        out << std::endl;
                    }
                }
            }
        }
    }
    return out;
}

// MULTIPLY EACH VALUE BY THE COEFFICIENT BY LOOPING THROUGH THE MATRIX AND USING *=
void Matrix::multiply_by_coefficient(const double& coefficient) {
    for (unsigned int i = 0; i < row_count; i++) {
        for (unsigned int j = 0; j < col_count; j++) {
            m_data[i][j] *= coefficient;
        }
    }
}


// SWAPPING ROWS WITH GIVEN ROW AND TARGET ROW TO CHANGE
bool Matrix::swap_row(const unsigned int& row_num, const unsigned int& target_row) {
    // IF EITHER ROW INPUTTED IS OUT OF BOUNDS RETURN FALSE
    if (row_num > row_count && target_row > row_count) { 
        return false;
    }
    else {
        // CREATING TEMPORARY POINTERS WITH INITIAL DATA AND SWAP BY SETTING M_DATA TO THE OPPOSITE POINTERS
        double* initial_row_nums = m_data[row_num];
        double* target_row_nums = m_data[target_row];
        m_data[row_num] = target_row_nums;
        m_data[target_row] = initial_row_nums;
        return true;
    }
}

// TRANSPOSE FUNCTION THAT SWAPS ROW AND COL SIZE AS WILL AS MOVE THE VALUES FROM ROW TO ROW TO COLUMN TO COLUMN
void Matrix::transpose() {
    double** temp_m_data;
    // CREATING A TEMPORARY ROW AND COL COUNT SO THE ORIGINAL CAN BE CHANGED LATER
    unsigned int temp_col_count = row_count;
    unsigned int temp_row_count = col_count;

    // CREATING A TEMPORARY MATRIX WITH COL_COUNT AS # OF ROWS AND ROW_COUNT AS # OF COLUMNS (OPPOSITE OF ORIGINAL)
    temp_m_data = new double*[col_count];
    for (unsigned int i = 0; i < col_count; i++) {
        temp_m_data[i] = new double[row_count];
    }  
    
    // SWAPPING DATA AT INDEX [i][j] to [j][i]
    for (unsigned int i = 0; i < row_count; i++) {
        for (unsigned int j = 0; j < col_count; j++) {
            temp_m_data[j][i] = m_data[i][j];
        }
    }
    
    // DELETING THE ORIGINAL INFORMATION IN THE MATRIX
    for(unsigned int i = 0; i < row_count; i++) {
        delete[] m_data[i];
    }
    delete[] m_data;

    // SETTING MATRIX EQUAL TO THE TEMP MATRIX TO FINALIZE CHANGES
    row_count = temp_row_count;
    col_count = temp_col_count;
    m_data = temp_m_data;
}  


// ADDING ONE MATRIX'S VALUES TO THE ORIGINAL MATRIX USING += OPERATOR WHEN ITERATING THROUGH EACH VALUE
bool Matrix::add(const Matrix& b) {
    // CHECK IF THE MATRICES ARE THE SAME SIZE FIRST
    if (row_count != b.row_count && col_count != b.col_count) {
        return false;
    }
    else {
        for (unsigned int i = 0; i < row_count; i++) {
            for (unsigned int j = 0; j < col_count; j++) {
                m_data[i][j] += b.m_data[i][j];
            }
        }
        return true;
    }
}

// SUBTRACTING ONE MATRIX'S VALUES TO THE ORIGINAL MATRIX USING -= OPERATOR WHEN ITERATING THROUGH EACH VALUE
bool Matrix::subtract(const Matrix& b) {
    // CHECK IF THE MATRICES ARE THE SAME SIZE FIRST
    if (row_count != b.row_count && col_count != b.col_count) {
        return false;
    }
    else {
        for (unsigned int i = 0; i < row_count; i++) {
            for (unsigned int j = 0; j < col_count; j++) {
                m_data[i][j] -= b.m_data[i][j];
            }
        }
        return true;
    }
}

// RETRIEVING A POINTER WITH A WHOLE ROW'S INFORMATION
double* Matrix::get_row(unsigned int row_num) {
    // IF THE ROW NUMBER REQUESTED IS OUT OF BOUNDS RETURN A NULL POINTER
    if (row_num >= row_count) {
        double* row_pointer = NULL;
        return row_pointer;
    }
    else{
        // ROW POINTER RETRIEVES AND ONLY HOLDS 1 ROW'S INFORMATION
        double* row_pointer = new double[col_count];
        for (unsigned int i = 0; i < col_count; i++) {
            row_pointer[i] = m_data[row_num][i];
        }
        return row_pointer;
    }
}

// RETRIEVING A POINTER WITH A WHOLE COLUMN'S INFORMATION
double* Matrix::get_col(unsigned int col_num) {
    // IF THE COLUMN NUMBER REQUESTED IS OUT OF BOUNDS RETURN A NULL POINTER
    if (col_num >= col_count) {
        double* col_pointer = NULL;
        return col_pointer;
    }
    else{
        // COL POINTER RETRIEVES AND ONLY HOLDS 1 ROW'S INFORMATION
        double* col_pointer = new double[row_count];
        for (unsigned int i = 0; i < row_count; i++) {
            col_pointer[i] = m_data[i][col_num];
        }
        return col_pointer;
    }
}


// QUARTER RETURNS A MATRIX OF 4 MATRIXES, WHERE EACH QUADRANT REPRESENTS CORNER VALUES
Matrix* Matrix::quarter() {
    Matrix *m_pointer = new Matrix[4]; // INITIALIZE A MATRIX OF POINTER OF SIZE 4
    
    // ROW SIZE AND COL SIZE GETS THE MIDDLE INDEX OF THE MATRIX
    // THIS REPRESENTS THE NEW QUADRANT'S SIZE
    unsigned int row_size;
    unsigned int col_size;
    if (row_count % 2 == 0) {
        row_size = row_count / 2;
    }
    // IF THE SIZE OF THE ORIGINAL IS ODD, THE QUADRANT ROW SIZE WILL BE THE ROW COUNT/TWO PLUS ONE
    else {
        row_size = (row_count / 2) + 1;
    }
    if (col_count % 2 == 0) {
        col_size = col_count / 2;
    }
    // IF THE SIZE OF THE ORIGINAL IS ODD, THE QUADRANT COL SIZE WILL BE THE COL COUNT/TWO PLUS ONE
    else { 
        col_size = (col_count / 2) + 1;
    }
    
    // LOOPING THROUGH POINTERS TO CREATE MATRIXES AT EACH POINTER
    for(int i = 0; i < 4; i++){
        Matrix temp(row_size,col_size,0);
        m_pointer[i] = temp;
    }

    // LOOPING THROUGH THE ROW_SIZE AND COL_SIZE B/C THAT WOULD BE EACH QUADRANT'S SIZE
    for (unsigned int i = 0; i < row_size; i++) {
        for (unsigned int j = 0; j < col_size; j++) {
            m_pointer[0].m_data[i][j] = m_data[i][j]; // QUADRANT UPPER LEFT
            m_pointer[1].m_data[i][j] = m_data[i][col_size+j]; // QUADRANT UPPER RIGHT
            m_pointer[2].m_data[i][j] = m_data[(row_size-1)+i][j]; // QUADRANT LOWER LEFT
            m_pointer[3].m_data[i][j] = m_data[(row_size-1)+i][col_size+j]; // QUADRANT LOWER RIGHT
        }
    }
    return m_pointer; // RETURN FINAL MATRIX OF MATRICES
}