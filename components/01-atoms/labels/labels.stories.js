import React from 'react';

import label from './label.twig';

import labelData from './label.yml';

/**
 * Storybook Definition.
 */
export default { title: 'Atoms/Labels' };

export const Label = () => (
  <div dangerouslySetInnerHTML={{ __html: label(labelData) }} />
);
