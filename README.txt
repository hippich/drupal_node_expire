This module allows users to either get notifications when a node hasn't been updated
in x amount of time, to automatically unpublish such "expired" nodes, and/or to receive
e-mail notifications and unpublish x days afterward.

Additional settings include allowing inheritance of the expiration settings from a book
page to its children, renotifications (Notify user every x days before unpublishing),
an email carbon copy address, and customizable email content.

In conjunction with book inheritance, an admin may decide who can and can't edit the
expiration times while the parent book settings are still inherited.

If the admin sets the automatic unpublishing to anything but "Immediate", an additional
page is available to view expired modules. ?q=admin/content/node/outdated

This module requires the use of Drupal's cron system for automatic unpublishing and
email notification features.

------------
Installation
------------

1. Copy the node_expire directory into your Drupal modules directory.

2. Go to Administer -> Site building -> Modules

3. Enable "Node Expire".

4. Go to Administer -> Site configuration -> Node Expire.

5. Edit the settings to your liking and push "Save Changes".

---------
Upgrading
---------

1. BACK UP YOUR DATA!

2. Copy the node_expire directory into your Drupal modules directory overriding previous files.

3. Run update.php.

4. Go to Administer -> Site configuration -> Node Expire.

5. Edit the settings to your liking and push "Save Changes".

----------------------------------------------
Displaying expiration dates on the node's page
----------------------------------------------

Open node.tpl.php for the template of choice and insert the following code:
<?php if ($expiration_type != 'none') { ?><span>Expires: <?php print $expire; ?></span><?php } ?>