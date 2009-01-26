NODE EXPIRE
===========

This module allows you to set a "timer" into content nodes. When it reaches zero,
you can perform any type of action with the node, such as unpublishing it or
sending an email to the author.

All this power is possible due Rules module. On each cron, Node Expire scan for
expired content and let Rules module work with it. You can select several actions
to perform with these nodes.

If using jQuery UI module, the date field will activate a Calendar widget in order
to make the process easiser and more fun.

If using Views module, all data will be exported, allowing you to build custom lists.


INSTALL
=======
This module is not (YET at least) compactible with previous versions. So its only
indicated to new sites.


CREDITS
=======
Daryl Houston     <daryl@learnhouston.com> (Original author)
Andrew Langland                            (D5-dev and D6-dev rewrite)
Bruno Massa                                (D6 v2 rewrite)