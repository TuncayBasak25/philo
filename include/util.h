/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 05:32:33 by tbasak            #+#    #+#             */
/*   Updated: 2025/08/07 00:09:40 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# define _DEFAULT_SOURCE
# define FNAME __func__
# define USE //__attribute__((warn_unused_result))

# define MAX_LEN -1

typedef unsigned char		t_uchar;
typedef unsigned char		t_u8;
typedef unsigned short		t_u16;
typedef unsigned int		t_u32;
typedef unsigned long long	t_u64;
typedef unsigned long long	t_usize;

typedef char				t_char;
typedef char				t_i8;
typedef short				t_i16;
typedef int					t_i32;
typedef long long			t_i64;
typedef long long			t_isize;

typedef float				t_f32;
typedef float				t_f64;

typedef t_char				*t_cstr;
typedef t_char				*t_cmstr;
typedef t_char const		*t_cvstr;

typedef enum e_result
{
	OK,
	FAIL
}	t_result;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_flow
{
	BREAK,
	CONTINUE
}	t_flow;

void
*mem_alloc(int size);

void
*mem_free(void *ptr);

t_usize
time_ms(void);

t_result
try_cvstr_into_usize(t_cvstr str, t_usize *out);

void
log_error(t_cvstr msg);

#endif