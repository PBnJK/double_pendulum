const statusElement = document.getElementById('status');
const progressElement = document.getElementById('progress');
const spinnerElement = document.getElementById('spinner');
const canvasElement = document.getElementById('canvas');

// As a default initial behavior, pop up an alert when webgl context is lost. To make your
// application robust, you may want to override this behavior before shipping!
// See http://www.khronos.org/registry/webgl/specs/latest/1.0/#5.15.2
canvasElement.addEventListener('webglcontextlost', (e) => {
  alert('WebGL context lost. You will need to reload the page.');
  e.preventDefault();
}, false);

var Module = {
  canvas: canvasElement,
  totalDependencies: 0,

  print(...args) {
    console.log(...args);
  },

  setStatus(text) {
    Module.setStatus.last ??= {
      time: Date.now(),
      text: ''
    };

    if (text === Module.setStatus.last.text) {
      return;
    }

    const m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
    const now = Date.now();

    // if this is a progress update, skip it if too soon
    if (m && now - Module.setStatus.last.time < 30) {
      return;
    }

    Module.setStatus.last.time = now;
    Module.setStatus.last.text = text;

    if (m) {
      text = m[1];
      progressElement.value = parseInt(m[2])*100;
      progressElement.max = parseInt(m[4])*100;
      progressElement.hidden = false;
      spinnerElement.hidden = false;
    } else {
      progressElement.value = null;
      progressElement.max = null;
      progressElement.hidden = true;

      if (!text) {
        spinnerElement.style.display = 'none';
      }
    }

    statusElement.innerHTML = text;
  },

  monitorRunDependencies(left) {
    this.totalDependencies = Math.max(this.totalDependencies, left);
    Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies-left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
  },

  onRuntimeInitialized() {
    const rangeL1 = document.getElementById("l1");
    const rangeL1Min = document.getElementById("l1-range-min");
    const rangeL1Max = document.getElementById("l1-range-max");
    const rangeCurrentL1 = document.getElementById("l1-current");

    rangeL1Min.textContent = rangeL1.min;
    rangeL1Max.textContent = rangeL1.max;

    const rangeL2 = document.getElementById("l2");
    const rangeL2Min = document.getElementById("l2-range-min");
    const rangeL2Max = document.getElementById("l2-range-max");
    const rangeCurrentL2 = document.getElementById("l2-current");

    rangeL2Min.textContent = rangeL2.min;
    rangeL2Max.textContent = rangeL2.max;

    const rangeB1Mass = document.getElementById("b1-mass");
    const rangeB1MassMin = document.getElementById("b1-mass-range-min");
    const rangeB1MassMax = document.getElementById("b1-mass-range-max");
    const rangeCurrentB1Mass = document.getElementById("b1-mass-current");

    rangeB1MassMin.textContent = rangeB1Mass.min;
    rangeB1MassMax.textContent = rangeB1Mass.max;

    const rangeB2Mass = document.getElementById("b2-mass");
    const rangeB2MassMin = document.getElementById("b2-mass-range-min");
    const rangeB2MassMax = document.getElementById("b2-mass-range-max");
    const rangeCurrentB2Mass = document.getElementById("b2-mass-current");

    rangeB2MassMin.textContent = rangeB2Mass.min;
    rangeB2MassMax.textContent = rangeB2Mass.max;

    const rangeG = document.getElementById("gravity");
    const rangeGMin = document.getElementById("g-range-min");
    const rangeGMax = document.getElementById("g-range-max");
    const rangeCurrentG = document.getElementById("g-current");

    rangeGMin.textContent = rangeG.min;
    rangeGMax.textContent = rangeG.max;

    rangeL1.oninput = (e) => {
      const value = e.target.value;

      rangeCurrentL1.textContent = `${value}cm`;
      Module.ccall("update_l1", null, ["number"], [value]);
    };

    rangeL2.oninput = (e) => {
      const value = e.target.value;

      rangeCurrentL2.textContent = `${value}cm`;
      Module.ccall("update_l2", null, ["number"], [value]);
    };

    rangeB1Mass.oninput = (e) => {
      const value = e.target.value;

      rangeCurrentB1Mass.textContent = `${value}g`;
      Module.ccall("update_b1_mass", null, ["number"], [value * 0.001]);
    };

    rangeB2Mass.oninput = (e) => {
      const value = e.target.value;

      rangeCurrentB2Mass.textContent = `${value}g`;
      Module.ccall("update_b2_mass", null, ["number"], [value * 0.001]);
    };

    rangeG.oninput = (e) => {
      const value = e.target.value;

      rangeCurrentG.innerHTML = `${value}m/s<sup>2</sup>`;
      Module.ccall("update_g", null, ["number"], [value]);
    };
  }
};
Module.setStatus('Downloading...');
window.onerror = (event) => {
  // TODO: do not warn on ok events like simulating an infinite loop or exitStatus
  Module.setStatus('Exception thrown, see JavaScript console');
  spinnerElement.style.display = 'none';
  Module.setStatus = (text) => {
    if (text) console.error('[post-exception status] ' + text);
  };
};

