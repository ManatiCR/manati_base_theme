import React from 'react';

import buttonList from './button-list.twig';

import buttonListData from './button-list.yml';
import buttonListAltData from './button-list-alt.yml';

/**
 * Storybook Definition.
 */
export default { title: 'Molecules/Button List' };

export const buttonListExample = () => (
  <div dangerouslySetInnerHTML={{ __html: buttonList(buttonListData) }} />
);

export const buttonListAltExample = () => (
  <div dangerouslySetInnerHTML={{ __html: buttonList(buttonListAltData) }} />
);
