import * as THREE from 'https://cdn.skypack.dev/three@0.129.0/build/three.module.js';
import { OrbitControls } from 'https://cdn.skypack.dev/three@0.129.0/examples/jsm/controls/OrbitControls.js';

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight, 1, 10000 );

const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

const geometry = new THREE.BoxGeometry( 1.2, 0.1, 0.6 );
const material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
const cube = new THREE.Mesh( geometry, material );
scene.add( cube );

const axesHelper = new THREE.AxesHelper( 5 );
console.log(axesHelper)
// axesHelper.setColors(new THREE.Color('red'), new THREE.Color('blue'), new THREE.Color('green'))
scene.add( axesHelper );
const controls = new OrbitControls( camera, renderer.domElement );

//controls.update() must be called after any manual changes to the camera's transform
camera.position.set( 0, 20, 100 );
controls.update();

function animate() {
    cube.position.x = Px;
    cube.position.y = -Py;
    cube.position.z = Pz;
    cube.rotation.x = Rx;
    cube.rotation.y = Ry;
    cube.rotation.z = Rz;
    controls.update();
	renderer.render( scene, camera );
	requestAnimationFrame( animate );
}
animate();