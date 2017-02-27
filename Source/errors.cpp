#include <string>
#include "errors.h"

const char* BaseError::what() const throw() {
    return msg.c_str();
}

BaseError::BaseError(int line, int pos, std::string msg) {
    this->msg = msg + "line = " + std::to_string(line) + " pos = " + std::to_string(pos);
}

UnexpectedEOF::UnexpectedEOF(int line, int pos): BaseError(line, pos, "Unexpected end of file: ") {}

UnterminatedString::UnterminatedString(int line, int pos): BaseError(line, pos, "Unterminated string: ") {}

UnterminatedComment::UnterminatedComment(int line, int pos): BaseError(line, pos, "Unterminated comment: ") {}

IncorrectFloat::IncorrectFloat(int line, int pos): BaseError(line, pos, "Incorrect float number: ") {}

IncorrectInteger::IncorrectInteger(int line, int pos): BaseError(line, pos, "Incorrect integer number: ") {}

IncorrectOperation::IncorrectOperation(int line, int pos): BaseError(line, pos, "Inccorect operation: ") {}

IncorrectFile::IncorrectFile(std::string fileName) {
    msg =  "Can't open file: \"" + fileName + "\"";
}

IncorrectBinary::IncorrectBinary(int line, int pos): BaseError(line, pos, "Incorrect binary number: ") {}

UnexpectedSymbol::UnexpectedSymbol(int line, int pos): BaseError(line, pos, "Unexpected symbol: ") {}
