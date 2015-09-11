<?php

/**
 * Implements hook_views_data_alter().
 */
function views_certificates_views_data_alter(&$data) {
  $data['certificate_node']['table']['group'] = t('Certificates');

  $data['certificate_node']['table']['base'] = array(
    'field' => 'cnid',
    'title' => t('Certificate Node'),
    'help' => t('Certificate cnid.'),
  );

  $data['certificate_node']['table']['entity type'] = 'certificate_node';

  $data['certificate_node']['table']['join'] = array(
    'course_report' => array(
      'left_table' => 'course_report',
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  $data['certificate_node']['table']['join'] = array(
    'node' => array(
      'left_table' => 'node',
      'left_field' => 'nid',
      'field' => 'template',
    ),
  );

  $data['certificate_node']['cnid'] = array(
    'title' => t('Certificate ID'),
    'help' => t('The certificate ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['certificate_node']['nid'] = array(
    'title' => t('Certificate Course ID'),
    'help' => t('The certificate course ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'course_report',
      'base field' => 'nid',
      'field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Certificate Course ID'),
      'title' => t('Certificate Course ID'),
      'help' => t('Relate the certificate to course.'),
    ),
  );

  $data['certificate_node']['template'] = array(
    'title' => t('Certificate Template Node ID'),
    'help' => t('The certificate template node ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'node',
      'base field' => 'nid',
      'field' => 'template',
      'handler' => 'views_handler_relationship',
      'label' => t('Certificate Template Node ID'),
      'title' => t('Certificate Template Node ID'),
      'help' => t('Relate the certificate to template node.'),
    ),
  );
}
