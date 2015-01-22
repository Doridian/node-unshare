var binding;

try {
  binding = require('../build/default/unshare');
}
catch (e) {
  binding = require('../build/Release/unshare');
}

module.exports = binding;
