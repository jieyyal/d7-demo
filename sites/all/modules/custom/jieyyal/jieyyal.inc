<?php
/*
 * Migration class to import profiles to profile2.
 */
class JieyyalMigration extends Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Migrate profiles to profile2');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'uid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationProfile2::getKeySchema()
    );
    

    $query = db_select('users', 'u')
      ->fields('u', array('uid'));
    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationProfile2('main');
    // Assign mappings TO destination fields FROM source fields. To discover
    $this->addFieldMapping('field_profile_first_name', 'profile_fname');
  }
  public function prepareRow($row) {
    $profile_fields = db_select('profile_values', 'pv')
      ->fields('pv', array('fid', 'value'))
      ->condition('uid', $row->uid)
      ->condition('fid', 2)
      ->execute()
      ->fetchAllKeyed();
    $this->profile_fname = $profile_fields[1];
  }
}
