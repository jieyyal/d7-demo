<?php

/**
 * @file
 * Implements for OG vocab with the module views.
 */

/**
 * Implements hook_views_data().
 */
/**
 * Implements hook_views_data().
 */
function og_vocab_views_data() {
  $data['og_vocab_relation']['table']['group']  = t('OG Vocabulary per Group');

  $data['og_vocab_relation']['table']['base'] = array(
    'title' => t('OG vocabulary'),
    'help' => t('OG vocabulary relation base table.'),
  );

  $data['og_vocab_relation']['vid'] = array(
    'title' => t('OG Vocabulary'),
    'help' => t('Term from a OG vocabulary.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'taxonomy_term_data',
      'base field' => 'vid',
      'title' => t('OG vocabulary Term'),
      'label' => t('Vocabulary'),
    ),
  );
  $data['og_vocab_relation']['gid'] = array(
    'title' => t('Group ID'),
    'help' => t('Filter per Group ID.'),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}
