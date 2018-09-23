#ifndef MARIAN_DATAFRAME_HPP
#define MARIAN_DATAFRAME_HPP

#include <string>
#include <vector>
#include <iostream>
#include <map>

namespace marian {
  class DataEntryClerk;

  /** \ingroup utils
   *  \brief Class used to handle data.
   *
   * Class enables to load the csv file and read it contents. 
   * One can access the single cell or read whole columns. 
   * Class allows to choose cell using column and row numbers or,
   * if defined, column names and primary keys. 
   *
   */
  
  class DataFrame {
  public:
    DataFrame(){};
    DataFrame(std::string file_name, char delimiter, bool first_row_is_column_names, int primery_key = 0);

    std::string operator()(const int col, const  int row);
    std::string operator()(const std::string col, const int row);
    std::string operator()(const std::string col, const std::string row);

    std::vector<std::string> operator()(int col);
    std::vector<std::string> operator()(std::string col);

    double getNumber(const int col, const  int row);
    double getNumber(const std::string col, const int row);
    double getNumber(const std::string col, const std::string row);

    std::vector<std::string> getColumnNames() const;
    std::vector<std::string> getPrimaryKeys() const;
    std::map<std::string, std::string> getRow(int row) const;
    
    void append(const DataEntryClerk&);
    void append(const DataFrame&);
    
    void print(int n_rows = -1);
    void printToCsv(std::string file_name, char delimiter = ';');
    
    int getNumberOfRows() const;
    int getNumberOfColumns() const;
    
    friend std::ostream& operator<<(std::ostream&, DataFrame&);
  private:
    void parseFile(std::string file_name, char delimiter);
    void createColumnNames(bool first_row);
    
    std::vector<std::vector<std::string> > data_; /*!< \brief Holds data as 2d table of strings*/
    std::map<std::string,int> column_names_;      /*!< \brief Maps column name to column number */
    std::map<std::string,int> primary_key_;       /*!< \brief Maps row name to row number*/
    int ncols_ = 0;                               /*!< \brief number of columns*/
    int nrows_ = 0;                               /*!< \brief number of rows*/
  };

  /** \ingroup utils
   *  \brief Class used to provide data to julian::DataFrame.
   * 
   * Class saves input provided by user. Data Clark passed as argument to julian::DataFrame::append
   * adds a new data row to DataFrame. Keys of the map are interpreted as column names and values as observation inputs.
   */
  class DataEntryClerk {
  public:

    /** \brief Default constructor
     */
    DataEntryClerk(){};
    void add(std::string, std::string);
    void add(std::string, double);
    void add(std::string, int);

    /** \brief add a map to data
     *
     * Method adds map to the . The values of the map provided must be one of the type accepted by julian::DataFrame::add methods
     */
    template<typename T>
    void add(const std::map<std::string, T>& input) {
      for (auto item : input)
	add(item.first, item.second);
    }
    
    friend class DataFrame;
  private:
    std::map<std::string, std::string> data_; /*!< \brief Maps that stores inputs provided using method DataEntryClerk::add.*/
  };
}  // namespace marian

#endif /* MARIAN_DATAFRAME_HPP */
