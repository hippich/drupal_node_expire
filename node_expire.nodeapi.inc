<?php
// $Id$

/**
 * @file
 * Node API integration.
 */

/**
 * Implementation of hook_nodeapi().
 */
function _node_expire_nodeapi(&$ntypes, &$node, $op, $a3 = NULL, $a4 = NULL) {
  switch ($op) {
    case 'load':
      $query = db_query('SELECT expire, expired
        FROM {node_expire} WHERE nid = %d', $node->nid);

      // Use the existing expiration data if present.
      if ($row = db_fetch_object($query)) {
        $node->expire   = $row->expire;
        $node->expired  = $row->expired;
      }
      break;

    case 'prepare':
      if (!isset($node->expire)) {
        $node->expire = format_date(strtotime($ntypes), 'custom', NODE_EXPIRE_FORMAT);
      }
      break;

    case 'validate':
      // The only restriction we have is that the node can't expire in the past.
      if ($node->expire <= 0) {
        form_set_error('expire_date', t('You have to specify a valid date.'));
      }
      elseif (strtotime($node->expire) <= time()) {
        form_set_error('expire_date', t("You can't expire a node in the past!"));
      }
      break;

    case 'update':
    case 'insert':
      $update = array();
      if (isset($node->node_expire)) {
        $update[] = 'nid';
      }
      $node->expire   = strtotime($node->expire);
      $node->expired  = FALSE;
      drupal_write_record('node_expire', $node, $update);
      break;

    case 'delete':
      db_query('DELETE FROM {node_expire} WHERE nid = %d', $node->nid);
      break;
  }
}
