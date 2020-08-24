void                ft_addback(t_env **p, char *environement)
{
    t_env *elem = malloc(sizeof(*elem));
    elem->content = environement;
    elem->next = NULL;
    if (*p){
        t_env *t = *p;
        while (t->next)
            t = t->next;
        t->next = elem;
    }
    else{
        *p = elem;
    }
}
