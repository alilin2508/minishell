void            ft_del_lst(t_env **p)
{
    t_env *tmp;

    tmp = *p;
    *p = (*p)->next;
    free(tmp);
}
