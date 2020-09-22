import React from 'react';

import fontSizeSwitcherTwig from './font-size-switcher.twig';

/**
 * Storybook Definition.
 */
export default { title: 'Molecules/Font Size Switcher' };

export const fontSizeSwitcher = () => (
  <div dangerouslySetInnerHTML={{ __html: fontSizeSwitcherTwig() }} />
);
