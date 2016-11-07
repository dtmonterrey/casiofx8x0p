/**
    Copyright 2016 Evandro Pires Alves

    This file is part of casiofx8x0p.

    casiofx8x0p is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    casiofx8x0p is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with casiofx8x0p.  If not, see <http://www.gnu.org/licenses/>.
  */

#ifndef BAUDRATE_H
#define BAUDRATE_H

#include <QString>

class BaudRate
{
public:
    BaudRate();
    BaudRate(const BaudRate &);
    BaudRate(int index, int value);
    ~BaudRate();
    QString toString();
    int getIndex();
    int getValue();
private:
    int index;
    int value;
};

#endif // BAUDRATE_H
