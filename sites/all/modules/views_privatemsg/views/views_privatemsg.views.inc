<?php

/**
 * @file
 * Provide views data alterations for privatemsg module.
 */

/**
 * Implements hook_views_data_alter().
 */
function views_privatemsg_views_data_alter(&$data) {

  // Message table.
  $data['pm_message']['table']['group'] = t('Privatemsg');

  $data['pm_message']['table']['base'] = array(
    'field' => 'mid',
    'title' => t('Private messages'),
    'help' => t('Private messages sent between users.'),
    'defaults' => array(
      'field' => 'body',
    ),
  );

  $data['pm_message']['table']['entity type'] = 'privatemsg_message';

  $data['pm_message']['table']['join'] = array(
    'pm_index' => array(
      'left_table' => 'pm_index',
      'left_field' => 'mid',
      'field' => 'mid',
    ),
  );

  $data['pm_message']['mid'] = array(
    'title' => t('Message ID'),
    'help' => t('The private message ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'pm_index',
      'field' => 'mid',
      'handler' => 'views_handler_relationship',
      'label' => t('Message index'),
      'title' => t('Message index'),
      'help' => t('Relate the message to threading info.'),
    ),
  );

  $data['pm_message']['author'] = array(
    'title' => t('Author'),
    'help' => t('The private message author.'),
    'field' => array(
      'help' => t('The UID of the private message author.'),
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'author',
      'handler' => 'views_handler_relationship',
      'label' => t('Author'),
      'help' => t('Relate to the user who sent the private message.'),
    ),
  );

  $data['pm_message']['subject'] = array(
    'title' => t('Subject'),
    'help' => t('The subject of the private message.'),
    'field' => array(
      'handler' => 'views_handler_field_pm_subject',
      'format' => array('field' => 'format'),
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['pm_message']['body'] = array(
    'title' => t('Message'),
    'help' => t('The text of the private message.'),
    'field' => array(
      'handler' => 'views_handler_field_pm_body',
      'format' => array('field' => 'format'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['pm_message']['timestamp'] = array(
    'title' => t('Send date'),
    'help' => t('The date and time when the message was sent.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // Message index table.
  $data['pm_index']['table']['group'] = t('Privatemsg');

  $data['pm_index']['table']['base'] = array(
    'field' => 'mid',
    'title' => t('Privatemsg threading index'),
    'defaults' => array(
      'field' => 'thread_id',
    ),
  );

  $data['pm_index']['table']['join'] = array(
    'pm_message' => array(
      'left_table' => 'pm_message',
      'left_field' => 'mid',
      'field' => 'mid',
    ),
  );

  $data['pm_index']['table']['entity type'] = 'privatemsg_message';

  $data['pm_index']['thread_id'] = array(
    'title' => t('Thread ID'),
    'help' => t('The ID of the private message thread.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'help' => t('Filter according to the thread privatemsgs belong to.'),
      'handler' => 'views_handler_argument_many_to_one',
    ),
  );
  $data['pm_index']['thread_link'] = array(
    'real field' => 'thread_id',
    'title' => t('Link to thread'),
    'help' => t('A link to the private message thread.'),
    'field' => array(
      'handler' => 'views_handler_field_pm_thread_link',
    ),
  );
  $data['pm_index']['delete_link']=array(
    'real field' => 'thread_id',
    'title' => t('Delete message'),
    'help' => t('A link to delete the private message.'),
    'field' => array(
      'handler' => 'views_handler_field_pm_delete_link',
    ),
  );
  $data['pm_index']['grouped_recipient']=array(
    'real field' => 'thread_id',
    'title' => t('Grouped recipient'),
    'help' => t('Grouped recipient.'),
    'field' => array(
      'handler' => 'views_handler_field_pm_recipient',
    ),
  );
  $data['pm_index']['recipient'] = array(
    'title' => t('Recipient'),
    'field' => array(
      'help' => t('The UID of the private message recipient.'),
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'help' => t("Filter according to the recipient's uid."),
      'handler' => 'views_handler_argument_user_uid',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'recipient',
      'handler' => 'views_handler_relationship',
      'label' => t('Recipient'),
      'help' => t('Relate to the user receiving the private message.'),
    ),
  );
  $data['pm_index']['is_new'] = array(
    'title' => t('Is new'),
    'help' => t('Whether the private message is unread.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'help' => t('Filter to private messages that have/have not been read.'),
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Show new'),
      'type' => 'yes-no',
    ),
  );
  $data['pm_index']['deleted'] = array(
    'title' => t('Is deleted'),
    'help' => t('Whether the private message has been deleted.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'help' => t('Filter to private messages that have/have not been deleted.'),
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Show deleted'),
      'type' => 'yes-no',
    ),
  );
  $data['pm_index']['type'] = array(
    'title' => t('Recipient type'),
    'help' => t('Recipient type'),
    'filter' => array(
      'help' => t('Filter to private messages recipient type.'),
      'handler' => 'views_handler_filter_in_operator',
      'label' => t('Show recipient type'),
      'options callback' => 'privatemsg_recipient_type_load',
    ),
  );

}

function privatemsg_recipient_type_load() {
  $types = privatemsg_recipient_get_types();
  $return = array();
  foreach ($types as $type => $item) {
    $return[$type] = $item['name'];
  }
  $return['hidden'] = t('Hidden');
  return $return;
}
