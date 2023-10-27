/*
 * stringlib.h
 *
 *  Created on: Oct 19, 2023
 *      Author: Ebram Habib
 */

#ifndef STRINGLIB_H_
#define STRINGLIB_H_

#define BUFF_MAX 40

s32 string_put(const s8*);
s8 string_get(s8* s);
s32 string_len(const s8* s);
s8 string_copy(s8* s1, const s8* s2);
s32 string_compare(const s8* s1, const s8* s2);
s32 string_ascii_to_int(const s8* s);


#endif /* STRINGLIB_H_ */
