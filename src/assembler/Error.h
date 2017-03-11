
/* Contain error generated during assembly
*/
class Error{
  public:
    int docNumber;
    int lineNumber;
    int wordNumber;
    QString cause;
    Error(int docNumber, int lineNumber, int wordNumber, QString cause){
      docNumber = docNumber;
      lineNumber = lineNumber;
      wordNumber = wordNumber;
      cause = cause;
    }
};

