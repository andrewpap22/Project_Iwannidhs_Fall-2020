#ifndef ETL_H
#define ETL_H

#include <iostream>
#include <fstream>
#include <Eigen/Dense>

class ETL
{
  std::string dataset; // accepts a filename as a string. (basically the dataset)
  std::string delimiter; // determines if columns in dataset are seperated by commas or tabs, etc...
  bool header; // indicates whether we have a header or not.

public:

  ETL(std::string data, std::string seperator, bool head) : dataset(data), delimiter(seperator), header(head)
  {
  }

};

#endif /* ETL_H */