/*
 * cia.h
 *
 *  Created on: 21 Oct 2016
 *      Author: johanwestlund
 */

#ifndef INCLUDE_CIA_H_
#define INCLUDE_CIA_H_

#define ROW 8
#define COL 8

/* This map corresponds to the keyboard matrix defined by Port A and Port B of CIA1 */
static const char KeyboardMap[ROW][COL] = {
        {'', '', '', '', '', '', '', ''}
};



#endif /* INCLUDE_CIA_H_ */
