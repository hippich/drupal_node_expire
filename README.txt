NODE EXPIRE
===========

This module allows you to set a "timer" into content nodes. When it reaches zero,
you can perform any type of action with the node, such as unpublishing it or
sending an email to the author.

All this power is possible due Rules module. On each cron, Node Expire scan for
expired content and let Rules module work with it. You can select several actions
to perform with these nodes.

If using jQuery UI module, the date field will activate a Calendar widget in order
to make the process easier and more fun.

If using Views module, all data will be exported, allowing you to build custom lists.


INSTALL
=======

This module is not (YET at least) compatible with previous versions. So its only
indicated to new sites.


USAGE
=====

The first thing you shuold do is give the proper permissions: "administer node expire"
will allow you to enable the feature on node types and put a default value. "edit
node expire" will allow you to put the real date on nodes.

Then you should go to admin/content/types and should the node type that will use
expiration feature. Under "Workflow settings", put the default expiration date
using PHP strtotime format.

Now, all users that have "edit node expire" will be able to select a diferent
expiration date during node creation/editing. If not, the default value will be
used. Note that if the user edit the node, the expiration date will not change.


CREDITS
=======

Daryl Houston     <daryl@learnhouston.com> (Original author)
Andrew Langland                            (D5-dev and D6-dev rewrite)
Bruno Massa                                (D6 v2 rewrite)
