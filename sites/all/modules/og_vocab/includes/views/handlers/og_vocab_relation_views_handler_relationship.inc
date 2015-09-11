<?php

/**
 * @file
 * A handler relationship for the OG vocabulary module.
 */

class og_vocab_relation_views_handler_relationship extends views_handler_relationship {

  /**
   * Overrides query().
   */
  function query() {
    parent::query();

    // Retrieving the group context of the user.
    $context = array();
    if (!module_exists('og_context')) {
      if (!empty($_SESSION['og_context'])) {
        $context = $_SESSION['og_context'];
      }
    }
    else {
      $context = og_context();
    }

    // The user is not in a group context, display all the og vocab terms.
    if (empty($context)) {
      return;
    }

    // Displaying only terms from OG vocabs that relate to the group.
    $this->query->add_where(NULL, 'og_vocab_relation_og_vocab.gid', $context['gid']);
    $this->query->add_where(NULL, 'og_vocab_relation_og_vocab.group_type', $context['group_type']);
  }
}
