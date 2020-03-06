#pragma once

#include <vector>
#include <cassert>

template <typename Type = int>
class Matrix
{
public:
	Matrix<Type>()
	{
		m_rows = 0;
		m_columns = 0;
	}

	Matrix<Type>(size_t _rows, size_t _columns)
	{
		assert(_rows > 0 && _columns > 0);

		m_rows = _rows;
		m_columns = _columns;
		m_data = std::vector<Type>(m_rows * m_columns, 0);
	}

	Matrix(const Matrix& other)
	{
		m_rows = other.m_rows;
		m_columns = other.m_columns;
		m_data = other.m_data;
	}

	~Matrix()
	{
		m_data.clear();
	}

	inline void insert(const size_t row, const size_t column, const Type value)
	{
		assert(row < m_rows);
		assert(column < m_columns);

		m_data[row * m_columns + column] = value;
	}

	Matrix get_transpose() const
	{
		Matrix matrix(m_columns, m_rows);

		for (size_t i = 0; i < m_columns; i++)
		{
			for (size_t j = 0; j < m_rows; j++)
			{
				matrix.m_data[i * m_rows + j] = m_data[j * m_columns + i];
			}
		}

		return matrix;
	}

	void transpose()
	{
		std::vector<Type> buffer(m_rows * m_columns);

		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_columns; j++)
			{
				buffer[j * m_rows + i] = m_data[i * m_columns + j];
			}
		}

		m_data = buffer;
		std::swap(m_rows, m_columns);
	}

	static Matrix dot(const Matrix& first, const Matrix& second)
	{
		assert(first.m_columns == second.m_rows);

		Matrix<Type> matrix(first.m_rows, second.m_columns);

		for (size_t i = 0; i < matrix.m_rows; i++)
		{
			for (size_t j = 0; j < matrix.m_columns; j++)
			{
				Type value = 0;

				for (size_t k = 0; k < first.m_columns; k++)
				{
					value += first.m_data[i * first.m_columns + k] *
							 second.m_data[k * second.m_columns + j];
				}

				matrix.m_data[i * matrix.m_columns + j] = value;
			}
		}

		return matrix;
	}

	inline const size_t rows() const
	{
		return m_rows;
	}

	inline const size_t columns() const
	{
		return m_columns;
	}

	Matrix operator+ (const Matrix& other) const
	{
		assert(m_rows == other.m_rows && m_columns == other.m_columns);

		Matrix<Type> matrix(m_rows, m_columns);

		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			matrix.m_data[i] = m_data[i] + other.m_data[i];
		}

		return matrix;
	}

	Matrix& operator+= (const Matrix& other)
	{
		assert(m_rows == other.m_rows && m_columns == other.m_columns);

		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			m_data[i] += other.m_data[i];
		}

		return *this;
	}

	Matrix operator- (const Matrix& other) const
	{
		assert(m_rows == other.m_rows && m_columns == other.m_columns);

		Matrix<Type> matrix(m_rows, m_columns);

		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			matrix.m_data[i] = m_data[i] - other.m_data[i];
		}

		return matrix;
	}

	Matrix& operator-= (const Matrix& other)
	{
		assert(m_rows == other.m_rows && m_columns == other.m_columns);

		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			m_data[i] -= other.m_data[i];
		}

		return *this;
	}

	Matrix operator* (const Matrix& other) const
	{
		assert(m_rows == other.m_rows && m_columns == other.m_columns);

		Matrix<Type> matrix(m_rows, m_columns);

		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			matrix.m_data[i] = m_data[i] * other.m_data[i];
		}

		return matrix;
	}

	Matrix<Type>& operator*= (const Matrix& other)
	{
		assert(m_rows == other.m_rows && m_columns == other.m_columns);
		
		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			m_data[i] *= other.m_data[i];
		}

		return *this;
	}

	Matrix& operator= (const Matrix& other)
	{
		m_rows = other.m_rows;
		m_columns = other.m_columns;
		m_data = other.m_data;

		return *this;
	}

	bool operator== (const Matrix& other)
	{
		if (m_rows != other.m_rows || m_columns != other.m_columns || m_data != other.m_data)
			return false;

		return true;
	}

	Matrix operator+ (const Type value)
	{
		Matrix<Type> matrix(m_rows, m_columns);
		
		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			matrix.m_data[i] = m_data[i] + value;
		}

		return matrix;
	}

	Matrix operator- (const Type value)
	{
		Matrix<Type> matrix(m_rows, m_columns);

		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			matrix.m_data[i] = m_data[i] - value;
		}

		return matrix;
	}


	Matrix operator* (const Type value)
	{
		Matrix<Type> matrix(m_rows, m_columns);

		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			matrix.m_data[i] = m_data[i] * value;
		}

		return matrix;
	}

	Matrix operator/ (const Type value)
	{
		Matrix<Type> matrix(m_rows, m_columns);

		for (size_t i = 0; i < m_rows * m_columns; i++)
		{
			matrix.m_data[i] = m_data[i] / value;
		}

		return matrix;
	}

	inline Type operator() (const size_t row, const size_t column) const
	{
		assert(row < m_rows);
		assert(column < m_columns);

		return m_data[row * m_columns + column];
	}

private:
	size_t m_rows;
	size_t m_columns;

	std::vector<Type> m_data;
};