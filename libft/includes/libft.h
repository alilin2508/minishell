/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grigo <grigo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:11:23 by grigo             #+#    #+#             */
/*   Updated: 2020/11/10 11:30:48 by grigo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_env
{
	char			*env;
	struct s_env	*next;
}				t_env;

typedef struct	s_envindex
{
	struct s_env	*head;
	struct s_env	*tail;
}				t_envindex;

char			*ft_strncat(char *dest, char *src, int nb);
char			*ft_strndup(const char *s, size_t n);
size_t			ft_strcspn(const char *s, const char *reject);
void			ft_putstr(const char *s);
char			*ft_strcpy(char *dest, char *src);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strcat(char *dest, char *src);
void			ft_del_lst(t_env **p);
void			ft_addback(t_env **p, char *environement);
int				ft_atoi(const char *str);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			ft_bzero(void *s, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strnstr(const char *haystack,
				const char *needle, size_t len);
char			*ft_strdup(const char *s1);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_itoa(long n);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_putendl(char const *s);
void			ft_memdel(void **ap);
t_list			*ft_lstnew(void const *content, size_t content_size);
char			*ft_strnew(size_t size);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_strdel(char **as);
char			*ft_strmerge(char *a, char *b);
int				ft_countwords(char *str, char sep);
void			ft_lstrev(t_list **alst);
int				ft_splitdel(char ***split);
size_t			ft_lstcount(t_list *lst);
int   		ft_strisdigit(char *str);

#endif
