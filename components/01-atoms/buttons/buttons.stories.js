import React from 'react';

import button from './button.twig';

import buttonData from './button.yml';

/**
 * Storybook Definition.
 */
export default { title: 'Atoms/Button' };

export const example = () => (
  <div dangerouslySetInnerHTML={{ __html: button(buttonData) }} />
);
