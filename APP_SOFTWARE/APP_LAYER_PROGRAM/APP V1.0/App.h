/*
 * App.h
 *
 *  Created on: Jun 30, 2022
 *      Author: dahroug
 */

#ifndef        APP_H_
#define        APP_H_

extern void                APP_vidInit (void);

extern void                APP_vidSetUp(void);

extern Std_enuErrorStatus  App_vidDisplayString(pu8 str);

extern void                APP_vidStartPov(void);


#endif         /* APP_H_ */
